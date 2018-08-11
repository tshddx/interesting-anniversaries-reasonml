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
    emoji: {js|🖌️|js},
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
  {
    name: "Derrick Rose",
    achievement: "he became the youngest player voted MVP in the NBA",
    birthday: d(1988, 10, 4),
    date: d(2011, 5, 3),
    emoji: {js|🏀|js},
  },
  {
    name: "Ben Roethlisberger",
    achievement: "he became the youngest NFL quarterback to win a Super Bowl",
    birthday: d(1982, 3, 2),
    date: d(2006, 2, 5),
    emoji: {js|🏈|js},
  },
  {
    name: "Charles Lindbergh",
    achievement: "he landed his plane in Paris, becoming the first person to fly solo across the Atlantic Ocean",
    birthday: d(1902, 2, 4),
    date: d(1927, 5, 21),
    emoji: {js|✈️|js},
  },
  {
    name: "Sir Edmund Hillary",
    achievement: "he and Tenzing Norgay became the first climbers to summit Mount Everest",
    birthday: d(1919, 7, 20),
    date: d(1953, 5, 29),
    emoji: {js|⛰️|js},
  },
  {
    name: "Martin Luther King Jr.",
    achievement: "he delivered his \"I Have a Dream\" speech in Washington, D.C.",
    birthday: d(1929, 4, 4),
    date: d(1963, 8, 28),
    emoji: {js|🎙️|js},
  },
  {
    name: "Linus Torvalds",
    achievement: "he released the very first version of Linux, now the most-used operating system in the world",
    birthday: d(1969, 12, 28),
    date: d(1991, 9, 17),
    emoji: {js|🖥️|js},
  },
  {
    name: "Marie Curie",
    achievement: "she received the Nobel Prize in Physics for her groundbreaking research on radioactivity",
    birthday: d(1867, 11, 7),
    date: d(1903, 12, 1),
    emoji: {js|📚|js},
  },
  {
    name: "Michelangelo",
    achievement: "he finished painting the ceiling of the Sistine Chapel (a 4-year endeavor)",
    birthday: d(1475, 3, 6),
    date: d(1512, 11, 1),
    emoji: {js|🎨|js},
  },
  {
    name: "Grigori Perelman",
    achievement: "he declined the Fields Medal (and a $1 million prize) after proving the Poincare conjecture in mathematics",
    birthday: d(1966, 6, 13),
    date: d(2006, 8, 1),
    emoji: {js|🏅|js},
  },
  {
    name: "Alan Turing",
    achievement: "he designed and built a computer to decrypt German communication during World War II",
    birthday: d(1912, 6, 23),
    date: d(1940, 3, 18),
    emoji: {js|👨‍💻|js},
  },
  {
    name: "Teddy Roosevelt",
    achievement: "he became the youngest President of the United States",
    birthday: d(1858, 10, 27),
    date: d(1901, 9, 14),
    emoji: {js|🇺🇸|js},
  },
  {
    name: "Isaac Newton",
    achievement: "he published Principia, establishing his famous theory of gravitation and laws of motion",
    birthday: d(1643, 1, 4),
    date: d(1687, 7, 1),
    emoji: {js|🍏|js},
  },
  {
    name: "J. R. R. Tolkien",
    achievement: "he published The Hobbit, which sold all initial 1,500 copies (followed by tens of millions more)",
    birthday: d(1892, 1, 2),
    date: d(1939, 9, 21),
    emoji: {js|📙|js},
  },
  {
    name: "Dorothy Davenhill Hirsch",
    achievement: "she became the oldest person to visit the North Pole",
    birthday: d(1915, 5, 11),
    date: d(2004, 8, 28),
    emoji: {js|❄️|js},
  },
];