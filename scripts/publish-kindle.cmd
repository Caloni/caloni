rem @echo off
copy /y layouts\book.html layouts\index.html
hugo --buildDrafts
git checkout layouts\index.html
pushd public\book
move /y ..\index.html .
sed -i "s/<pre><code>ascii art:/<h6 style=\"page-break-after: always\"><\/h6><pre><code>/" index.html
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ cp caloni.mobi k:\documents
popd
