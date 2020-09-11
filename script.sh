# Check if branch gh-pages exists
# https://stackoverflow.com/a/28776049
git rev-parse --verify gh-pages

if [ $? -eq 0 ]
then
  git branch -D gh-pages
fi

git checkout --orphan gh-pages

echo 'Generating index.html...\n'
echo 'Hellllooo' > index.html
echo 'Generating index.html is done!\n'

echo 'Pushing changes to remote gh-pages branch...\n'
git add . > /dev/null 2>&1
git commit -m "Update index.html" > /dev/null 2>&1
git push origin --force gh-pages > /dev/null 2>&1
echo 'Pushing changes to remote gh-pages branch is done!\n'

git checkout master

echo 'All done'
