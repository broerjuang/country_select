module type Config = {
  type t;
  let decoder_response: Atdgen_codec_runtime.Json.t => t;
};

module Make = (C: Config) => {
  type state =
    | Idle
    | Loaded(C.t)
    | Error(string)
    | Loading;

  type action =
    | FetchRequested
    | FetchFailed(string)
    | FechSucceed(C.t);

  let component = ReasonReact.reducerComponent("App");

  let make = (~url, ~method_, children) => {
    ...component,
    initialState: () => Idle,
    reducer: (action, state) => {
      switch (action) {
      | FetchRequested =>
        ReasonReact.UpdateWithSideEffects(
          state,
          self =>
            Js.Promise.(
              Fetch.fetchWithInit(url, Fetch.RequestInit.make(~method_, ()))
              |> then_(Fetch.Response.json)
              |> then_(response => {
                   let data = response |> C.decoder_response;
                   self.send(FechSucceed(data)) |> resolve;
                 })
              |> catch(_error =>
                   self.send(FetchFailed("Failed to fetch countries data"))
                   |> resolve
                 )
              |> ignore
            ),
        )
      | FetchFailed(message) => ReasonReact.Update(Error(message))
      | FechSucceed(data) =>
        ReasonReact.Update(
          {
            Loaded(data);
          },
        )
      };
    },
    didMount: self => {
      self.send(FetchRequested);
    },
    render: self => {
      children(self.state);
    },
  };
};