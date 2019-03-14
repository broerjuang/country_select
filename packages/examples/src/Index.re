open Country_bs;

let from_list_option_to_array_of_option = xs => {
  xs
  |> List.map(option_ => {"label": option_.label, "value": option_.value})
  |> Array.of_list;
};

module Fetch =
  Fetcher.Make({
    type t = Country_t.response;
    let decoder_response = json =>
      json |> Atdgen_codec_runtime.Decode.decode(Country_bs.read_response);
  });

ReactDOMRe.renderToElementWithId(
  <Fetch url="http://localhost:3000/country" method_=Get>
    ...{state =>
      switch (state) {
      | Idle => ReasonReact.null
      | Loading => ReasonReact.string("loading")
      | Loaded(d) =>
        let formatedOptions = d.data |> from_list_option_to_array_of_option;
        // Match the interface
        <Select>
          ...{({onSelect, selectedValue}) =>
            <div
              style={ReactDOMRe.Style.make(
                ~display="flex",
                ~flexDirection="row",
                ~justifyContent="space-evenly",
                ~alignItems="center",
                (),
              )}>
              <div>
                <p> {ReasonReact.string("without virtualized")} </p>
                <CountrySelect
                  onSelect
                  selectedValue
                  options=formatedOptions
                  withVirtualized=false
                />
              </div>
              <div>
                <p> {ReasonReact.string("with virtualized")} </p>
                <CountrySelect
                  onSelect
                  selectedValue
                  options=formatedOptions
                  withVirtualized=true
                />
              </div>
            </div>
          }
        </Select>;
      | Error(message) => ReasonReact.string(message)
      }
    }
  </Fetch>,
  "root",
);