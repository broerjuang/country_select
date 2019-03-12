module Select = {
  [@bs.module "react-select"]
  external reactClass: ReasonReact.reactClass = "default";

  // type component =

  // type components('a) = {. "Option": 'a => ReasonReact.reactElement};

  // [@bs.deriving jsConverter]
  // type style = {
  //   clearIndicator: ReactDOMRe.style => ReactDOMRe.Style.t,
  //   container: ReactDOMRe.style => ReactDOMRe.Style.t,
  //   control: ReactDOMRe.style => ReactDOMRe.Style.t,
  // };

  [@bs.obj]
  external makeProps:
    (
      ~autoFocus: bool=?,
      ~controlShouldRenderValue: bool=?,
      ~hideSelectedOptions: bool=?,
      ~isClearable: bool=?,
      ~menuIsOpen: bool=?,
      ~onChange: 'a => unit=?,
      ~options: array('a)=?,
      ~placeholder: string=?,
      ~tabSelectsValue: bool=?,
      ~components: 'b=?,
      ~backspaceRemovesValue: bool=?,
      ~maxMenuHeight: int=?,
      ~value: 'a=?,
      ~styles: 'c=?,
      unit
    ) =>
    _ =
    "";

  let make =
      (
        ~autoFocus=?,
        ~controlShouldRenderValue=?,
        ~hideSelectedOptions=?,
        ~isClearable=?,
        ~menuIsOpen=?,
        ~components=?,
        ~onChange=?,
        ~options=?,
        ~placeholder=?,
        ~tabSelectsValue=?,
        ~value=?,
        ~backspaceRemovesValue=?,
        ~maxMenuHeight=?,
        ~styles=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        makeProps(
          ~autoFocus?,
          ~controlShouldRenderValue?,
          ~hideSelectedOptions?,
          ~isClearable?,
          ~menuIsOpen?,
          ~onChange?,
          ~options?,
          ~placeholder?,
          ~tabSelectsValue?,
          ~components?,
          ~maxMenuHeight?,
          ~styles?,
          ~backspaceRemovesValue?,
          ~value?,
          (),
        ),
      children,
    );
};

module Components = {
  module Option = {
    [@bs.module "react-select"] [@bs.scope "components"]
    external reactClass: ReasonReact.reactClass = "Option";

    // Passing all options going down to component level, similar to spread the props, because react-select managed all of those
    let make = (~props, children) =>
      ReasonReact.wrapJsForReason(~reactClass, ~props, children);
  };

  module DropdownIndicator = {
    [@bs.module "react-select"] [@bs.scope "components"]
    external reactClass: ReasonReact.reactClass = "DropdownIndicator";

    let make = (~props, children) =>
      ReasonReact.wrapJsForReason(~reactClass, ~props, children);
  };
};