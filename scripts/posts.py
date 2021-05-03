import frontmatter
import glob

path = "content/posts/*.md"
verbose = False

def transform(operations):
  for fname in glob.glob(path):
    if verbose:
      print(fname)
    with open(fname, 'r', encoding='utf8') as f:
      post = frontmatter.load(f)
      for op in operations:
        op(post)
      post_str = frontmatter.dumps(post)
      f.close()
      with open(fname, 'w', encoding='utf8') as f:
        f.write(post_str)

def format():
  def nothing(post):
    pass
  transform([ nothing ])

def move_category_to_tag(category):
  def func(post):
    if post.get('categories') and category in post['categories']:
      if verbose:
        print('categories:', post['categories'])
      post['categories'].remove(category)
      if post.get('tags') and category not in post['tags']:
        post['tags'].append(category)
      else:
        post['tags'] = [ category ]
  transform([ func ])

