open Iterator;

let generate = (birthday, now) : list(Anniversary.t) => {
  let anniversaries = ref([]: list(Anniversary.t));
  let max_date = DateFns.addYears(150.0, birthday);
  let generators = InterestingNumber.generators |> from_list;
  let calculators = Anniversary.calculators |> from_list;
  let pairs = product(generators, calculators);
  pairs
  |> map(((generator, calculator)) => {
       let ff = 1;
       ();
       generator()
       |> map(number => calculator(birthday, number))
       |> take_while((anniversary: Anniversary.t) =>
            anniversary.date |> DateFns.isBefore(max_date)
          )
       |> to_list;
     })
  |> to_list
  |> List.concat
  |> List.sort((a: Anniversary.t, b: Anniversary.t)
       /* DateFns.compareAsc(a.Anniversary.date, b.Anniversary.date) */
       => compare(DateFns.getTime(a.date), DateFns.getTime(b.date)))
  |> List.filter((ann: Anniversary.t) =>
       DateFns.compareAsc(ann.date, now) >= 0
       && ann.Anniversary.date
       |> DateFns.isBefore(max_date)
     );
  /* Anniversary.achievements
     |> List.iter((achievement: Anniversary.achievement) => {
          let difference =
            DateFns.differenceInCalendarDays(
              achievement.date,
              achievement.birthday,
            );
          let date = DateFns.addDays(difference, birthday);
          anniversaries :=
            [{date, source: Achievement(achievement)}, ...anniversaries^];
        }); */
};