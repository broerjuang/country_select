module Select = {
  [@bs.deriving jsConverter]
  type commonProps = {
    label: string, // made up label and very opinioated with this apps
    value: string,
  };

  [@bs.deriving abstract]
  type components = {
    // Currently, I only care about this two field.
    // I need to refactor this when I got clear idea what props is passing here
    [@bs.optional] [@bs.as "Option"]
    options:
      {
        .
        "label": string,
        "value": string,
      } =>
      ReasonReact.reactElement,
    [@bs.optional] [@bs.as "DropdownIndicator"]
    dropdownIndicator: Js.t({.}) => ReasonReact.reactElement,
    [@bs.optional] [@bs.as "IndicatorSeparator"]
    indicatorSeparator: Js.t({.}) => ReasonReact.reactElement,
  };

  [@bs.deriving abstract]
  type styles('a) = {
    [@bs.optional]
    control: 'a => 'a,
    [@bs.optional]
    menu: 'a => 'a,
  };

  [@bs.module "react-select"]
  external reactClass: ReasonReact.reactClass = "default";

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
      ~components: components=?,
      ~backspaceRemovesValue: bool=?,
      ~maxMenuHeight: int=?,
      ~value: 'a=?,
      ~styles: styles(ReactDOMRe.Style.t)=?,
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
      ) => {
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