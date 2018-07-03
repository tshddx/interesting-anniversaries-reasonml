let component = ReasonReact.statelessComponent("AnniversaryList");

let make = (~anniversaries: array(Anniversary.t), ~isPast: bool, _children) => {
  ...component,
  render: _self => {
    let iterator = anniversaries |> Iterator.fromArray;
    /* |> Iterator.firstChunk((a, b) =>
         DateFns.isSameDay(a.Anniversary.date, b.Anniversary.date)
       ); */
    <div className="AnniversaryList">
      (
        iterator
        |> Iterator.toArray
        |> Array.mapi((index, ann: Anniversary.t) =>
             <div key=(string_of_int(index))>
               <AnniversaryItem
                 anniversary=ann
                 isPast
                 isToday=(DateFns.isToday(ann.date))
               />
             </div>
           )
        |> ReasonReact.array
      )
    </div>;
  },
};

type foo('state) =
  | Foo('state)
  | Bar
  | Baz;