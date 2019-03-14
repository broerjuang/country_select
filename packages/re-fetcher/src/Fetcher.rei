module type Config = {
  type t;
  let decoder_response: Atdgen_codec_runtime.Json.t => t;
};
module Make:
  (C: Config) =>
   {
    type state =
      | Idle
      | Loaded(C.t)
      | Error(string)
      | Loading;
    type action =
      | FetchRequested
      | FetchFailed(string)
      | FechSucceed(C.t);
    let component:
      ReasonReact.componentSpec(
        state,
        ReasonReact.stateless,
        ReasonReact.noRetainedProps,
        ReasonReact.noRetainedProps,
        action,
      );
    let make:
      (
        ~url: string,
        ~method_: Fetch.requestMethod,
        state => ReasonReact.reactElement
      ) =>
      ReasonReact.componentSpec(
        state,
        state,
        ReasonReact.noRetainedProps,
        ReasonReact.noRetainedProps,
        action,
      );
  };