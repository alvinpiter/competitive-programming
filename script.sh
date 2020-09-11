echo "Doing magic ..."

# Check if branch gh-pages exists
# https://stackoverflow.com/a/28776049
git rev-parse --verify gh-pages

if [ $? -eq 0 ]
then
  git branch -D gh-pages
fi

git checkout --orphan gh-pages

echo "Hellllooo" > index.html

git add .
git commit -m "Update index.html"
git push origin --force gh-pages

git checkout master

echo "Done pushing code to branch gh-pages"
