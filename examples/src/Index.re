open Country_bs;

let from_list_option_to_array_of_option = xs => {
  xs
  |> List.map(option_ => {"label": option_.label, "value": option_.value})
  |> Array.of_list;
};

ReactDOMRe.renderToElementWithId(
  <App>
    ...{({state, send}) =>
      switch (state.status) {
      | Idle => ReasonReact.null
      | Error(message) => ReasonReact.string(message)
      | Loaded(countries) =>
        let formatedOptions = countries |> from_list_option_to_array_of_option;
        <CountrySelect
          onSelect={value => send(SelectValue(value))}
          selectedValue={state.selectedValue}
          options=formatedOptions
        />;
      | Loading => ReasonReact.string("loading ..")
      }
    }
  </App>,
  "root",
);