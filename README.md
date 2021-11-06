# Interesting Anniversaries

Have you ever wanted to know when you turn 2 billion seconds old? How about
33,333,333 minutes old? When do you get to celebrate your 555,555th hour of
life? As it turns out, all three of those milestones occur in the same 24-hour
period! Head over to
[Interesting Anniversaries](https://interesting-anniversaries.com/) to see
when you can celebrate your interesting anniversaries.

# Installation

Install all dependencies:

```
$ yarn
```

# Development

Run the following two tasks in two separate tabs (and keep them running).

- Run BuckleScript to watch ReasonML `.re` files for changes and compile them to
  JavaScript (the `.js` files get put in `lib/js/src/` and are git ignored):

  ```
  yarn run start
  ```

- Run the webpack dev server to watch JavaScript files in `lib/js/src/` for
  changes and compile them into one bundle (at `build/app.js`):

  ```
  yarn run dev
  ```

# Building for production

Run `yarn run webpack:production` to generate the `index.html` and `app.js`
files in the `build/` directory.
