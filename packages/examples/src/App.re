open Country_bs;

type status =
  | Idle
  | Loaded(list(country))
  | Error(string)
  | Loading;

type state = {
  status,
  selectedValue: option(string),
};

type action =
  | FetchRequested
  | FetchFailed(string)
  | FechSucceed(list(Country_t.country))
  | SelectValue(string);

let component = ReasonReact.reducerComponent("App");

let make = children => {
  ...component,
  initialState: () => {status: Idle, selectedValue: None},
  reducer: (action, state) => {
    switch (action) {
    | FetchRequested =>
      ReasonReact.UpdateWithSideEffects(
        {...state, status: Loading},
        self =>
          Js.Promise.(
            Fetch.fetchWithInit(
              "http://localhost:3000/country",
              Fetch.RequestInit.make(~method_=Get, ()),
            )
            |> then_(Fetch.Response.json)
            |> then_(response => {
                 let countries =
                   response
                   |> Atdgen_codec_runtime.Decode.decode(
                        Country_bs.read_response,
                      );

                 self.send(FechSucceed(countries.data)) |> resolve;
               })
            |> catch(_error =>
                 self.send(FetchFailed("Failed to fetch countries data"))
                 |> resolve
               )
            |> ignore
          ),
      )
    | FetchFailed(message) =>
      ReasonReact.Update({...state, status: Error(message)})
    | FechSucceed(countries) =>
      ReasonReact.Update({...state, status: Loaded(countries)})
    | SelectValue(value) =>
      ReasonReact.Update({...state, selectedValue: Some(value)})
    };
  },
  didMount: self => {
    self.send(FetchRequested);
  },
  render: self => {
    children(self);
  },
};