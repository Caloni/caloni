rem @echo off
copy /y layouts\book.html layouts\index.html
hugo --buildDrafts
pushd public
move /y index.html book.html
sed -i "s/<pre><code>ascii art:/<h6 style=\"page-break-after: always\"><\/h6><pre><code>/" book.html
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ copy /y caloni.mobi k:\documents
popd
git checkout layouts\index.html
