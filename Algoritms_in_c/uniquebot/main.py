from typing import Final
from telegram import Update, Bot
from telegram.ext import Application, CommandHandler, MessageHandler, filters, ContextTypes, ConversationHandler
import requests
from bs4 import BeautifulSoup
from datetime import datetime, timedelta

TOKEN: Final = '7790894801:AAHRtm_wNBoYv38d6U_pFclzSSYbs0lnc8k'
BOT_USERNAME: Final = '@unique_job_bot'

bot = Bot(token=TOKEN)

# States for ConversationHandler
JOB_TYPE, LOCATION, PREFERENCE = range(3)

# Commands
async def start_command(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text('Hello! Thanks for chatting with me! I am a unique job finder!')

async def help_command(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text('I am a unique job finder! Please type something so I can respond!')

async def custom_command(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text('This is a custom command!')

# Job Fetching
def fetch_jobs(job_type, location, remote):
    jobs = []
    current_time = datetime.utcnow()
    time_threshold = current_time - timedelta(hours=24)

    # Fetch jobs from Indeed
    indeed_url = f'https://www.indeed.com/jobs?q={job_type}&l={location}'
    indeed_response = requests.get(indeed_url)
    indeed_soup = BeautifulSoup(indeed_response.content, 'html.parser')
    indeed_jobs = indeed_soup.find_all('div', class_='jobsearch-SerpJobCard')
    for job in indeed_jobs:
        post_date = job.find('span', class_='date').text.strip()
        if 'hour' in post_date or ('day' in post_date and int(post_date.split()[0]) <= 1):
            jobs.append(job)

    return jobs

def format_job_message(job):
    title = job.find('a', class_='jobtitle').text.strip()
    company = job.find('span', class_='company').text.strip()
    location = job.find('span', class_='location').text.strip()
    job_link = f"https://www.indeed.com{job.find('a', class_='jobtitle')['href']}"

    return f'Title: {title}\nCompany: {company}\nLocation: {location}\nJob Link: {job_link}'

# Conversation Handlers
async def job_type_handler(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text('Please enter the type of job you are looking for (e.g., Software Engineer).')
    return JOB_TYPE

async def location_handler(update: Update, context: ContextTypes.DEFAULT_TYPE):
    context.user_data['job_type'] = update.message.text
    await update.message.reply_text('Please enter the location where you are looking for a job.')
    return LOCATION

async def preference_handler(update: Update, context: ContextTypes.DEFAULT_TYPE):
    context.user_data['location'] = update.message.text
    await update.message.reply_text('Do you prefer remote or in-office jobs?')
    return PREFERENCE

async def fetch_jobs_handler(update: Update, context: ContextTypes.DEFAULT_TYPE):
    context.user_data['preference'] = update.message.text
    job_type = context.user_data.get('job_type')
    location = context.user_data.get('location')
    preference = context.user_data.get('preference')

    jobs = fetch_jobs(job_type, location, preference)

    if not jobs:
        await update.message.reply_text('No jobs found within the last 24 hours.')
    else:
        for job in jobs:
            job_message = format_job_message(job)
            await update.message.reply_text(job_message)

    return ConversationHandler.END

async def cancel_handler(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text('Job search canceled.')
    return ConversationHandler.END

# Responses
def handle_response(text: str) -> str:
    processed: str = text.lower()

    if 'hello' in processed:
        return 'Hey there!'
    
    if 'how are you' in processed:
        return 'I am good!'
    
    if 'i love python' in processed:
        return 'Remember to subscribe'
    
    return 'I do not understand what you wrote...'

async def handle_message(update: Update, context: ContextTypes.DEFAULT_TYPE):
    message_type: str = update.message.chat.type
    text: str = update.message.text

    print(f'User ({update.message.chat.id}) in {message_type}: "{text}"')

    if message_type == 'group':
        if BOT_USERNAME in text:
            new_text: str = text.replace(BOT_USERNAME, '').strip()
            response:str = handle_response(new_text)
        else:
            return
    else:
        response: str = handle_response(text)

    print('Bot:', response)
    await update.message.reply_text(response)

async def error(update: Update, context: ContextTypes.DEFAULT_TYPE):
    print(f'Update {update} caused error {context.error}')

if __name__ =='__main__':
    print('Starting bot...')
    app = Application.builder().token(TOKEN).build()

    # Conversation handler for job search
    conv_handler = ConversationHandler(
        entry_points=[CommandHandler('jobsearch', job_type_handler)],
        states={
            JOB_TYPE: [MessageHandler(filters.TEXT & (~filters.COMMAND), location_handler)],
            LOCATION: [MessageHandler(filters.TEXT & (~filters.COMMAND), preference_handler)],
            PREFERENCE: [MessageHandler(filters.TEXT & (~filters.COMMAND), fetch_jobs_handler)],
        },
        fallbacks=[CommandHandler('cancel', cancel_handler)]
    )

    # Add handlers to the application
    app.add_handler(conv_handler)
    app.add_handler(CommandHandler('start', start_command))
    app.add_handler(CommandHandler('help', help_command))
    app.add_handler(CommandHandler('custom', custom_command))

    # Messages
    app.add_handler(MessageHandler(filters.TEXT, handle_message))

    # Errors
    app.add_error_handler(error)

    # Polls the bot
    print('Polling...')
    app.run_polling(poll_interval=3)

