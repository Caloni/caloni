rem @echo off
copy /y layouts\book.html layouts\index.html
hugo --buildDrafts
git checkout layouts\index.html
pushd public\book
move /y ..\index.html .
sed -i "s/href=\"\//href=\"#/g" index.html
sed -i "s/href=\"#[a-z]\+\/[a-z.-]\+/href=\"#/g" index.html
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ cp caloni.mobi k:\documents
popd
