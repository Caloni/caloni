import frontmatter
import glob

path = "content/posts/*.md"

def format():
  for fname in glob.glob(path):
    with open(fname, 'r', encoding='utf8') as f:
      post = frontmatter.load(f)
      post_str = frontmatter.dumps(post)
      f.close()
      with open(fname, 'w', encoding='utf8') as f:
        f.write(post_str)

