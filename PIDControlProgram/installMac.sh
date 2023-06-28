

# check if there is a folder called 
# q: where can i learn this if [ ! -d "./Dependencies" ];
# a: https://stackoverflow.com/questions/59838/check-if-a-directory-exists-in-a-shell-script
# q: i want to learn more about shell script
# a: https://www.shellscript.sh/quickref.html
if [ ! -d "./Dependencies" ]; then
  mkdir Dependencies
fi
cd ./Dependencies
# clone the git repo for the project, it conatains all versions commited before
git clone https://github.com/udacity/CarND-Path-Planning-Project.git
# copy from https://github.com/uNetworking/uWebSockets/releases?page=15, left side of the version
git checkout e94b6e1