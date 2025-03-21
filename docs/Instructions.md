# How to have many main.cpp files to test different codes into de robot:

In the src/ folder, you can have as many files as you want but just one is going to be the `main.cpp`

If you want to have different versions of codes that you want to run, you need to create one enviornment for each version on the `platformio.ini` file 

## Example and instructions

For this example, we have 2 versions of code. One file for each.
```
main.cpp
Test_Photo.cpp
```
these files are on the src/ folder

### Create the enviornment
On the `platformio.ini` file, there would be an enviornment for each code
On the first place, there would just be one enviornment for the `main.cpp` that was created automaticaly with the project

In an example where we create a simple project to work with an arduino uno, a default enviornment would look like this:

![Example of a default enviornment creation](resources/default_enviornment.png)

where:
```
[env:NAME] = you can name your enviornment as you want
platform = in which platform are you working
board = which board are you using
framework = arduino
lib_deps = librarys that you need for your code
```
***Note that `lib_deps` is not included by default***

In this example, we are working on a teensy. The environment for the `main.cpp` would be:

![Example of the enviornment of the main file](resources/Teensy_env1.png)

We also create a new enviornment for testing specific functions

![Example of the enviornment of the TestCode.cpp](resources/Teensy_env2.png)


In this case where we have different codes, is important to make sure that on `lib_deps` just include the libraries you would use in that specific code. Don't include all libraries in all enviornments if you are not using all of them in all your code versions.

### Compiling and uploading to robot

On VSCode, you need to chose which enviornment do you want to compile and upload to your robot

Click where it says the default enviornment you are working at

![Where does it says which enviornment are you working on](resources/default_env_work.png)

Thene, chose the enviornment you want. It should apear with the name you called your enviornment

![Options to chose the enviornment you want to work on](resources/chose_default_env.png)

*** Note that there is also the option of running a command on the terminal but it didn't work when we try it.***

### Make sure to run just the code you want to run

We want to make sure that the platform just run one main file. To do that, you need to specify on the `platformio.ini` file adding the folowing line:

```
src_filter = +<FILE YOU WANT TO RUN> -<FILE OR FILES YOU DONT WANT TO RUN>
```

For example:

On the enviornment we want to run the `main.cpp` file, our line should be like this:
```
src_filter = +<main.cpp> -<photo_test.cpp>
```
On the enviornment we want to run the `Test_Photo.cpp` file, our line should be like this:

```
src_filter = +<Test_Photo.cpp> -<main.cpp>
```

### enviornments configuration
The final configuration with our 2 code versions should look like this

![Final enviornment configuration](resources/final_env_config.png)

# Important

Check the `platform.ini` file to see how the differente enviornments are configurated

### ***If you want to explore this and more info, check [the oficial platformIO documentation](https://docs.platformio.org/en/latest/what-is-platformio.html)***