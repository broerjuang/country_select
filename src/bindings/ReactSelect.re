module Shared = {
  [@bs.deriving jsConverter]
  type commonProps = {
    label: string, // made up label and very opinioated with this apps
    value: string,
  };

  [@bs.deriving abstract]
  type components('a) = {
    // Currently, I only care about this two field.
    // I need to refactor this when I got clear idea what props is passing here
    [@bs.optional] [@bs.as "Option"]
    options: 'a => ReasonReact.reactElement,
    [@bs.optional] [@bs.as "DropdownIndicator"]
    dropdownIndicator: Js.t({.}) => ReasonReact.reactElement,
    [@bs.optional] [@bs.as "IndicatorSeparator"]
    indicatorSeparator: Js.t({.}) => ReasonReact.reactElement,
    [@bs.optional] [@bs.as "MenuList"]
    menuList: 'a => ReasonReact.reactElement,
  };

  [@bs.deriving abstract]
  type styles('a) = {
    [@bs.optional]
    control: 'a => 'a,
    [@bs.optional]
    menu: 'a => 'a,
  };
};

module Select = {
  open Shared;
  [@bs.module "react-select"]
  external reactClass: ReasonReact.reactClass = "default";

  [@bs.obj]
  external makeProps:
    (
      ~autoFocus: bool=?,
      ~className: string=?,
      ~closeMenuOnSelect: bool=?,
      ~controlShouldRenderValue: bool=?,
      ~hideSelectedOptions: bool=?,
      ~isClearable: bool=?,
      ~menuIsOpen: bool=?,
      ~onChange: 'a => unit=?,
      ~options: array('a)=?,
      ~placeholder: string=?,
      ~tabSelectsValue: bool=?,
      ~components: components('b)=?,
      ~backspaceRemovesValue: bool=?,
      ~maxMenuHeight: int=?,
      ~filterOption: bool=?,
      ~value: option(string)=?,
      ~styles: styles(ReactDOMRe.Style.t)=?,
      unit
    ) =>
    _ =
    "";

  let make =
      (
        ~autoFocus=?,
        ~className=?,
        ~closeMenuOnSelect=?,
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
        ~filterOption=?,
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
          ~className?,
          ~closeMenuOnSelect?,
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
          ~filterOption?,
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

  module MenuList = {
    [@bs.module "react-select"] [@bs.scope "components"]
    external reactClass: ReasonReact.reactClass = "MenuList";

    let make = (~props, children) =>
      ReasonReact.wrapJsForReason(~reactClass, ~props, children);
  };
};