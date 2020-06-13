#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Simple Bot to reply to Blogue do Caloni searches based on echobot.py sample.

author Wanderley Caloni <wanderley.caloni@gmail.com>
date 2020-06

If you want to install it as a Ubuntu/raspberry service do as follows.

1. Create a file named calonibot.service with the content bellow.

```
[Service]
WorkingDirectory=/var/usr/calonibot
ExecStart=/usr/bin/python3 /var/usr/calonibot/calonibot.py
Restart=always
StandardOutput=syslog
StandardError=syslog
SyslogIdentifier=calonibot
User=root
Group=root
Environment=NODE_ENV=production
[Install]
WantedBy=multi-user.target
```

2. Keep the working directory for this repo writable for the user that is
going to use it as a service.

3. You are done.

Obs.: this script is going to update itself from time to time in order to
catch the lastest commits and search for newer posts properly. So take care
of keep its source conflict free.
"""
import sys
import logging
import telegram
from telegram.error import NetworkError, Unauthorized
from telegram import InlineQueryResultArticle
import xml.etree.ElementTree as ET
from time import sleep
import urllib.request
from git import Repo
import json
import re
import argparse

update_id = None
thumb_url_sample = "http://caloni.com.br/images/caloni.png"

response_sample = [

    InlineQueryResultArticle('1'
        , u'Wanderley Caloni'
        , telegram.InputTextMessageContent('https://caloni.com.br/caloni/')
        , url='https://caloni.com.br/caloni/'
        , thumb_url=thumb_url_sample)

    , InlineQueryResultArticle('2'
        , 'Search'
        , telegram.InputTextMessageContent('https://caloni.com.br/search/')
        , url='https://caloni.com.br/search/'
        , thumb_url=thumb_url_sample)
]


def request_posts(path):
    tree = ET.parse(path) if path else None
    return tree


def find_posts(regex, root):
    lastLink = None
    links = []

    counter = 1
    if root:
        for item in root.iter('item'):
            title = item.find('title').text
            desc = item.find('description').text
            detail = item.find('details').text
            link = item.find('link').text
            mt = re.search(regex, title, flags=re.I) 
            md = desc if desc == None else re.search(regex, desc, flags=re.I) 
            md2 = detail if detail == None else re.search(regex, detail, flags=re.I) 
            if mt or md or md2:
                content = telegram.InputTextMessageContent(link)
                links.append(InlineQueryResultArticle(str(counter), title, content, url=link, description=desc, thumb_url=thumb_url_sample))
                counter += 1
                if counter > 50: break
    else:
        links = response_sample

    return links[0:50]


def echo(params, bot):
    """Echo the message the user sent."""
    global update_id
    if params.repo:
        try:
            repo = Repo(params.repo)
            repo.remotes[0].pull("master")
        except Exception as e:
            print("exception trying to pull repo " + params.repo + ": " + str(e))
    # Request updates after the last update_id
    for update in bot.get_updates(offset=update_id, timeout=10):
        update_id = update.update_id + 1

        if update.inline_query:
            regex = update.inline_query['query']
            posts = request_posts(params.rss)
            response = find_posts(regex, posts)
            update.inline_query.answer(response)


def main():

    argparser = argparse.ArgumentParser('Caloni BOT')
    argparser.add_argument('--auth', help="Telegram authorization token.")
    argparser.add_argument('--rss', help="RSS file to search.")
    argparser.add_argument('--repo', help="Git repo working dir; update it if provided.")
    argparser.add_argument('--find-post', help="Find single post test.")
    params = argparser.parse_args()

    if params.find_post:
        lines = request_posts(params.rss)
        resp = find_posts(params.find_post, lines)
        for r in resp:
            print(r)
        return

    logger = logging.getLogger()
    logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    logger.setLevel(logging.DEBUG)

    """Run the bot."""
    global update_id
    global response
    # Telegram Bot Authorization Token
    bot = telegram.Bot(params.auth)

    # get the first pending update_id, this is so we can skip over it in case
    # we get an "Unauthorized" exception.
    try:
        update_id = bot.get_updates()[0].update_id
    except IndexError:
        update_id = None

    logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')

    while True:
        try:
            echo(params, bot)
        except NetworkError:
            sleep(1)
        except Unauthorized:
            # The user has removed or blocked the bot.
            update_id += 1


if __name__ == '__main__':
    main()

