/* `birthday` is the birthday of the achiever, and `date` is the date that
   person achieved the achievement. */
type t = {
  name: string,
  achievement: string,
  birthday: Js.Date.t,
  date: Js.Date.t,
  emoji: string,
};

let d = (year, month, day) =>
  Js.Date.makeWithYMD(
    float_of_int(year),
    float_of_int(month - 1),
    float_of_int(day),
    (),
  );

let emoji = {js|🏆|js};

let achievements = [
  {
    name: "Albert Einstein",
    achievement: "he published his famous E=mc^2 equation",
    birthday: d(1879, 3, 14),
    date: d(1905, 11, 21),
    emoji: {js|🧠|js},
  },
  {
    name: "Mark Zuckerberg",
    achievement: "he launched Facebook from his dorm room",
    birthday: d(1984, 5, 14),
    date: d(2004, 2, 1),
    emoji: {js|👤|js},
  },
  {
    name: "Neil Armstrong",
    achievement: "he became the first human to set foot on the Moon",
    birthday: d(1930, 8, 5),
    date: d(1969, 7, 21),
    emoji: {js|👨‍🚀|js},
  },
  {
    name: "Pablo Picasso",
    achievement: "he finished his masterpiece \"Guernica\"",
    birthday: d(1881, 10, 25),
    date: d(1937, 6, 4),
    emoji: {js|🎨|js},
  },
  {
    name: "Ludwig van Beethoven",
    achievement: "he debuted his Symphony No. 5 in Vienna",
    birthday: d(1770, 12, 17),
    date: d(1808, 12, 22),
    emoji: {js|🎼|js},
  },
  {
    name: "Mary Shelley",
    achievement: "she published \"Frankenstein; or, The Modern Prometheus\"",
    birthday: d(1797, 8, 30),
    date: d(1818, 1, 1),
    emoji: {js|📚|js},
  },
  {
    name: "Ada Lovelace",
    achievement: "she wrote the first ever computer program, in 1843",
    birthday: d(1815, 12, 10),
    /* Published in Septermber according to
       http://www.yorku.ca/christo/papers/Babbage-CogSci.htm */
    date: d(1843, 9, 1),
    emoji: {js|👩‍💻|js},
  },
];