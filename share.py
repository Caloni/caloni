# coding=utf8
import twitter
import sys
import re
import shutil
import subprocess
import urllib
from urllib.request import urlopen
import time
import glob
from PIL import Image
import os
import webbrowser
import git

sys.path.append(".auth")
import twitter_caloni as twitter_credentials
import medium_caloni as medium_credentials

baseUrl = 'http://caloni.com.br/' 


def PrintStars(stars):
    ret = ''
    starFull = chr(0x2605)
    starEmpty = chr(0x2606)
    for s in range(0, int(stars)):
        ret = ret + starFull
    for s in range(int(stars), 5):
        ret = ret + starEmpty
    ret = ret + ' '
    return ret


def PublishToTwitter(postInfo, img):
    """
    https://pypi.python.org/pypi/twitter
    """
    t = twitter.Twitter(auth=twitter_credentials.auth)
    t_up = twitter.Twitter(domain='upload.twitter.com', auth=twitter_credentials.auth)
    id_img1 = ''
    
    if img:
        print('opening image', img, 'to share')
        imgUrl = urlopen(img)
        img = imgUrl.read()
        id_img1 = t_up.media.upload(media=img)["media_id_string"]

    stars = PrintStars(postInfo['stars']) if 'stars' in postInfo else ''
    remaining = 130 - len(stars + ' ' + postInfo['subtitle'] + '\n' + '\n' + postInfo['shortlink'])
    st = stars + ' ' + postInfo['subtitle'] + '\n' + postInfo['shortlink']
    t.statuses.update(status=st, media_ids=",".join([id_img1]))


def PublishToMedium(postInfo, img):
    #if img:
    #    print('opening image', img, 'to share')
    #    imgUrl = urlopen(img)
    #    img = imgUrl.read()

    user = medium_credentials.client.get_current_user()
    content = postInfo['content'] + '\n\nFrom: ' + postInfo['shortlink']
    post = medium_credentials.client.create_post(user_id=user['id'], title=postInfo['subtitle'], content=content, content_format="markdown")


def GetPermalinkFromCommit(ref):
	g = git.Repo('.')
	ci = g.commit(ref)
	for f, d in ci.stats.files.items():
		if f.find('content') != -1 and f.find('cinemaqui') == -1:
			return f[f.find('/')+1:f.rfind('.')]


def GetCommentFromCommit(ref):
	g = git.Repo('.')
	ci = g.commit(ref)
	return ci.message


def GetPostInfo(ref):
    post = GetPermalinkFromCommit(ref) 
    postInfo = { 'file' : 'content\\' + post.replace('/', '\\') + '.md' }
    postInfo['permalink'] =  post if post.find('post/') == -1 else post[post.find('/')+1:]
    postInfo['category'] = 'movies' if post.find('post/') != -1 else post[:post.rfind('/')]
    postInfo['link'] = baseUrl + postInfo['permalink'] + '/'
    postInfo['shortlink'] = postInfo['link']
    comment = GetCommentFromCommit(ref)
    postInfo['subtitle'] = comment
    postInfo['content'] = ""
    content = False

    infos = {
        'title': '^title: \"(.*)\"',
        'stars': '^stars: \"([1-5])/5\"',
        'category': '^category: \"(.*)\"',
        'cabine': '^cabine: \"(.*)\"',
        'desc': '^desc: \"(.*)\"',
        'imdb': '^imdb: \"(.*)\"',
        'img': '^img: \"(.*)\"',
    }
    file = open(postInfo['file'], encoding='utf8')
    for line in file.readlines():
        if content == True:
            postInfo['content'] += line
            pass
        if line.find("---") == 0 and 'title' in postInfo:
            content = True
        for key, search in infos.items():
            match = re.match(search, line)
            if match:
                postInfo[key] = match.group(1)

    print(postInfo)
    return postInfo


def FindPostImageAndPrepare(postInfo):
    ScreenshotBaseWidth = 725
    imgs = glob.glob('*.jpg')
    if len(imgs) > 0 :
        origPath = imgs[0]
        newPath = postInfo['permalink'] + '.jpg'
        img = Image.open(origPath)
        wpercent = (ScreenshotBaseWidth/float(img.size[0]))
        hsize = int((float(img.size[1])*float(wpercent)))
        img = img.resize((ScreenshotBaseWidth, hsize), Image.ANTIALIAS)
        img.save(newPath)
        if origPath != newPath:
            os.remove(origPath)


def PublishToSocialMedia(ref, img):
    try:
        print('getting post info')
        postInfo = GetPostInfo(ref)
        webbrowser.open_new_tab(baseUrl)
        input('if the page is ok type enter ' + postInfo['link'])

        print('publishing to twitter')
        PublishToTwitter(postInfo, img if img else postInfo['img'] if 'img' in postInfo else None)
        PublishToMedium(postInfo, img if img else postInfo['img'] if 'img' in postInfo else None)
        if postInfo['link'].find('/movies/') != -1:
            print('share on letterboxd, please')
            webbrowser.open_new_tab('http://www.letterboxd.com/imdb/' + postInfo['imdb'])
        print('everything is awewome')
    except Exception as e:
        print('something gone wrong')
        raise


if len(sys.argv) < 2:
    print('How to use: python share.py commit [http://image-link]')
else:
    PublishToSocialMedia(sys.argv[1], None if len(sys.argv) < 3 else sys.argv[2])

