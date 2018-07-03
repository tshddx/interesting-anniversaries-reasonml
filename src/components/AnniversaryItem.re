let component = ReasonReact.statelessComponent("AnniversaryItem");

let make =
    (~anniversary: Anniversary.t, ~isPast: bool, ~isToday: bool, _children) => {
  ...component,
  render: _self => {
    let isToday = DateFns.isToday(anniversary.date);
    let date = anniversary.date |> Utils.df;
    <div className="AnniversaryItem">
      <Icon anniversary />
      <div className="AnniversaryItem__description">
        <Description anniversary isPast isToday />
      </div>
      /* <div className="AnniversaryItem__description">
           (
             ReasonReact.string(
               AnniversaryText.sentence(anniversary, isPast, isToday),
             )
           )
         </div> */
      <div className="AnniversaryItem__share">
        <button> (ReasonReact.string("T")) </button>
        <button> (ReasonReact.string("F")) </button>
      </div>
    </div>;
  },
};