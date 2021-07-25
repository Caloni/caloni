import posts
import subprocess
import sys
import pyperclip

if len(sys.argv) > 1:
  file = "posts/{}.md".format(sys.argv[1])
  proc = subprocess.Popen("hugo new {}".format(file), stdout=subprocess.PIPE, shell=True)
  proc.wait()
  if proc.returncode == 0:
    clip = pyperclip.paste().splitlines()
    def edit(post):
      post['title'] = clip[0]
      post.content = '\n'.join(clip[2:])
    posts.transform([ edit ], [ 'content/' + file ])
else:
  print('How to use: new [slug]')

