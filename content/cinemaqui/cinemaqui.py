import sys
import os
import glob
import imdb
import yaml
import urllib
import urllib2
import datetime
import simplejson


PostsPath = r'C:\daytoday\cinetenisverde.github.io\cinemaqui'
access = imdb.IMDb()
forceUpdate = len(sys.argv) > 1 and sys.argv[1] == '--force-update'
specificReview = len(sys.argv) > 1 and sys.argv[1].find('.md') != -1


def loadreview(filePath):
  f = open(filePath)
  nextLine = f.readline()
  if nextLine == '---\n':
    header = ''
    nextLine = f.readline()
    while nextLine != '---\n':
      header = header + nextLine
      nextLine = f.readline()
    review = f.read()
    header = yaml.load(header)
    return header, review
  return None


def writereview(filePath, header, review, imdbData):

  def replace(item, macro, s, separator = ', '):
    if imdbData.has_key(item):
      if isinstance(imdbData[item], unicode):
        return s.replace(macro, imdbData[item].encode('utf-8'))
      elif isinstance(imdbData[item], list):
        items = ''
        for c in range(0, min(5, len(imdbData[item]))):
          i = imdbData[item][c]
          if isinstance(i, unicode):
            if items != '':
              items = items + separator + i.encode('utf-8')
            else:
              items = i.encode('utf-8')
          else:
            if items != '':
              items = items + separator + str(i)
            else:
              items = str(i)
        return s.replace(macro, items)
      else:
        return s.replace(macro, str(imdbData[item]))
    else:
      return s

  f = open(filePath, 'w')
  f.write('---\n')
  for k, v in header.iteritems():
    if k in ['imdb', 'title', 'date']:
      if isinstance(v, basestring):
        v = '"' + v.encode('utf-8') + '"'
      elif isinstance(v, datetime.datetime) or isinstance(v, datetime.date):
        v = v.isoformat()
      f.write(str(k) + ': ' + str(v) + '\n')
  f.write('categories: "cinemaqui"\n')
  f.write('draft: "true"\n')
  f.write('---\n')

  f.write(review)

  bottom1 = '\n<hr>"OriginalTitle" (Countries, Year), escrito por Writers, dirigido por Directors, com Cast<hr>\n'
  bottom1 = replace('title', 'OriginalTitle', bottom1)
  bottom1 = replace('countries', 'Countries', bottom1, '/')
  bottom1 = replace('year', 'Year', bottom1)
  bottom1 = replace('writer', 'Writers', bottom1)
  bottom1 = replace('director', 'Directors', bottom1)
  bottom1 = replace('cast', 'Cast', bottom1)
  f.write(bottom1)

  bottom2 = '\n<h2>Trailer - Title<h2>\n'
  bottom2 = bottom2.replace('Title', header['title'].encode('utf-8'))
  f.write(bottom2)

  f.close()


def updatereview(filePath):
  header, review = loadreview(filePath)
  if header.has_key('imdb'):
    imdbId = int(header['imdb'])
    movieData = access.get_movie(imdbId)
    writereview(filePath, header, review, movieData)


if len(sys.argv) > 1:
  updatereview(sys.argv[1])

