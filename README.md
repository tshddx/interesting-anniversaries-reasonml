# Interesting Anniversaries

Have you ever wanted to know when you turn 2 billion seconds old? How about 33,333,333 minutes old? When do you get to celebrate your 555,555th hour of life? As it turns out, all three of those milestones occur 




# Reason React Starter

This contains my modifications to the `bsb -init` starter project from the
official docs: https://reasonml.github.io/reason-react/docs/en/installation.html

# Installation

Clone this repo into a new directory and `cd` into it:

```
$ git clone --depth=1 https://github.com/baddox/reason-react-starter.git MyApp
$ cd MyApp
```

Install all dependencies:

```
$ yarn
```

Remove the `.git` directory so that we can start over as a new repo:

```
$ rm -rf .git
```

Initialize a new repo for this directory (e.g. by following GitHub's
instructions after [creating a new repo](https://github.com/new)).

# Development

Run the following two tasks in two separate tabs (and keep them running).

* Run BuckleScript to watch ReasonML `.re` files for changes and compile them to
  JavaScript (the `.js` files get put in `lib/js/src/` and are git ignored):

  ```
  yarn run start
  ```

* Run the webpack dev server to watch JavaScript files in `lib/js/src/` for
  changes and compile them into one bundle (at `build/app.js`):

  ```
  yarn run dev
  ```

# Building for production

Choose a name for your app in `bsconfig.json` and `package.json` (it should be
the same name in both).

Run `yarn run webpack:production` to generate the `index.html` and `app.js`
files in the `build/` directory.

# Todo

* Consolidate the BuckleScript and webpack npm tasks into just one (presumably
  get webpack to do it all?) dev server).
* Figure out how to require and build CSS (eject reason-scripts and see how they
  do it in their webpack config).
* Figure out Yeoman or something to allow "forking" this starter project into
  new projects without removing the `.git` directory.
