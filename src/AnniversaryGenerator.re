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
  let anniversaries = ref([]);
  pairs^
  |> List.iter(((generator, calculator)) => {
       let anns = generator() |> List.map(calculator(birthday));
       anniversaries := anniversaries^ @ anns;
     });
  anniversaries^
  |> List.sort((a, b)
       /* DateFns.compareAsc(a.Anniversary.date, b.Anniversary.date) */
       =>
         compare(
           DateFns.getTime(a.Anniversary.date),
           DateFns.getTime(b.Anniversary.date),
         )
       )
  |> List.filter(ann =>
       DateFns.compareAsc(ann.Anniversary.date, now) >= 0
       && ann.Anniversary.date
       |> DateFns.isBefore(surelyDead)
     );
};