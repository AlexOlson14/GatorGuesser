# GatorGuesser
## 3rd Place Overall out of 90 teams @ [SwampHacks IX](https://2023.swamphacks.com/)
### [Devpost Submission](https://devpost.com/software/gatorguesser)
### Watch the [video demo](https://youtu.be/e9dYN9_obXI)!

## Inspiration
Our main inspiration for this project was to explore the unknown and encourage our fellow gators to do the same by testing their knowledge of the campus we know(?) and love.

## What it does
Our app is inspired by the popular game GeoGuessr in which the player is dropped into a random place on Google Street View and has to guess where they are on a map. In our game, the user is dropped into a random place on the UF campus, and they have to guess where they are on the map. The closer they guess, the more points they earn!

## How we built it
The front end of the app was built using the SFML library for c++. This handles displaying graphics and taking user input. The backend of the app is also based in c++, and the images in our app were all gathered on campus during the hackathon. 

## Challenges we ran into
One challenge we ran into was how to get the precise location of nearly 150 images from around campus without manually entering each one. To solve this problem, we methodically extracted the metadata from our pictures to obtain the latitude and longitude which we load into our program and interpret into our virtual map.

## Accomplishments that we're proud of
We are proud of the game we created because we didn't just create a finished game, but we also made it scalable! 

## What we learned
SFML is tricky, and uploading/downloading/converting large piles of pictures can be frustrating. We also learned that with a dedicated team and time to focus, you can accomplish a lot in just 36 hours!

## What's next for GatorGuesser
We plan to keep cleaning it up and adding new features like game modes, timed matches, and variable difficulty. Another feature we are interested in the ability for individuals to submit their own images from around campus to be added into the game.

## Instructions:
To run the code and play our game, clone the repo onto your local machine, then run the file `GatorGuesser/GatorGuesser.exe`.
