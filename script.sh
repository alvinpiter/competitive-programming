# Check if branch gh-pages exists
# https://stackoverflow.com/a/28776049
git rev-parse --verify gh-pages > /dev/null 2>&1

if [ $? -eq 0 ]
then
  git branch -D gh-pages > /dev/null 2>&1
fi

git checkout --orphan gh-pages > /dev/null 2>&1

printf 'Generating index.html...\n'
echo 'Script v3' > index.html
printf 'Generating index.html is done!\n'

printf 'Pushing changes to remote gh-pages branch...\n'
git add . > /dev/null 2>&1
git commit -m "Update index.html" > /dev/null 2>&1
git push origin --force gh-pages > /dev/null 2>&1
printf 'Pushing changes to remote gh-pages branch is done!\n'

git checkout master > /dev/null 2>&1

printf 'All done!\n'
