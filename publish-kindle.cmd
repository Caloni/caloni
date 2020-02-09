rem @echo off
copy /y layouts\book.html layouts\index.html
hugo
pushd public
move /y index.html book.html
sed -i "s/href=\"\//href=\"#/g" book.html
sed -i "s/src=\"\//src=\"/g" book.html
sed -i "s/href=\"#images/href=\"images/g" book.html
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ copy /y caloni.mobi k:\documents
popd
git checkout layouts\index.html
