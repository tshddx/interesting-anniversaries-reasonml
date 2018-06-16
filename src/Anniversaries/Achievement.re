/* birthday is the birthday of the achiever, and date is the date that person
   achieved the achievement. */
type t = {
  name: string,
  achievement: string,
  birthday: Js.Date.t,
  date: Js.Date.t,
};

let d = (year, month, day) =>
  Js.Date.makeWithYMD(
    float_of_int(year),
    float_of_int(month - 1),
    float_of_int(day),
    (),
  );

let achievements = [
  {
    name: "Albert Einstein",
    achievement: "he published his famous E=mc^2 equation",
    birthday: d(1879, 3, 14),
    date: d(1905, 11, 21),
  },
  {
    name: "Mark Zuckerberg",
    achievement: "he launched Facebook from his dorm room",
    birthday: d(1984, 5, 14),
    date: d(2004, 2, 1),
  },
  {
    name: "Neil Armstrong",
    achievement: "he became the first human to set foot on the Moon",
    birthday: d(1930, 8, 5),
    date: d(1969, 7, 21),
  },
  {
    name: "Pablo Picasso",
    achievement: "he finished his masterpiece \"Guernica\"",
    birthday: d(1881, 10, 25),
    date: d(1937, 6, 4),
  },
];