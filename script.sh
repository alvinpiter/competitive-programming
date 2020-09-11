set -e

printf 'Setting git name and email...\n\n'
git config user.name
git config user.email
printf 'Setting git name and email is done!\n\n'

printf 'Preparing gh-pages branch...\n\n'
# Check if branch gh-pages exists
# https://stackoverflow.com/a/28776049
if git rev-parse --verify gh-pages; then
  git branch -D gh-pages
fi

git checkout --orphan gh-pages
printf 'Preparing gh-pages branch is done!\n\n'

printf 'Generating index.html...\n\n'
echo 'Script v5' > index.html
printf 'Generating index.html is done!\n\n'

printf 'Pushing changes to remote gh-pages branch...\n\n'
git add .
git commit -m "Update index.html" > /dev/null 2>&1
git push https://${GITHUB_TOKEN}@github.com/alvinpiter/competitive-programming.git --force gh-pages
printf 'Pushing changes to remote gh-pages branch is done!\n\n'

printf 'All done!\n'
