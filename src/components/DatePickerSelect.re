let component = ReasonReact.statelessComponent("DatePickerSelect");

let defaultValue = "";

let getValue = event => ReactDOMRe.domElementToObj(
                          ReactEventRe.Form.target(event),
                        )##value;

let make =
    (
      ~options: array((string, string)),
      ~value: option(string),
      ~defaultLabel: string,
      ~onChange: string => unit,
      ~disabled=false,
      ~className="",
      _children,
    ) => {
  ...component,
  render: _self => {
    let options' =
      switch (value) {
      | Some(_) => options
      | None => Array.append([|(defaultValue, defaultLabel)|], options)
      };
    let value' = value |> Utils.optionDefault(defaultValue);
    <select
      className=("DatePicker__select" ++ " " ++ className)
      value=value'
      onChange=(
        event => {
          let value = getValue(event);
          if (value !== defaultValue) {
            onChange(value);
          };
        }
      )
      disabled>
      (
        options'
        |> Array.map(((value, label)) =>
             <option key=value value> (ReasonReact.string(label)) </option>
           )
        |> ReasonReact.array
      )
    </select>;
  },
};