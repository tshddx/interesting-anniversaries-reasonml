let generate = (birthday, now) => {
  let surelyDead = DateFns.addYears(150.0, birthday);
  let pairs = ref([]);
  InterestingNumber.generators
  |> List.iter(generator =>
       Anniversary.calculators
       |> List.iter(calculator =>
            pairs := [(generator, calculator), ...pairs^]
          )
     );
  let anniversaries = ref([]: list(Anniversary.t));
  pairs^
  |> List.iter(((generator, calculator)) => {
       let anns = generator() |> List.map(calculator(birthday));
       anniversaries := anniversaries^ @ anns;
     });
  Anniversary.achievements
  |> List.iter((achievement: Anniversary.achievement) => {
       let difference =
         DateFns.differenceInCalendarDays(
           achievement.date,
           achievement.birthday,
         );
       let date = DateFns.addDays(difference, birthday);
       anniversaries :=
         [{date, source: Achievement(achievement)}, ...anniversaries^];
     });
  anniversaries^
  |> List.sort((a: Anniversary.t, b: Anniversary.t)
       /* DateFns.compareAsc(a.Anniversary.date, b.Anniversary.date) */
       => compare(DateFns.getTime(a.date), DateFns.getTime(b.date)))
  |> List.filter((ann: Anniversary.t) =>
       DateFns.compareAsc(ann.date, now) >= 0
       && ann.Anniversary.date
       |> DateFns.isBefore(surelyDead)
     );
};