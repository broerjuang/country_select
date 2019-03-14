[@bs.module "react-window"]
external reactClass: ReasonReact.reactClass = "FixedSizeList";

let make =
    (~height=300, ~itemCount, ~itemSize, ~initialScrollOffset, children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={
      "height": height,
      "itemCount": itemCount,
      "itemSize": itemSize,
      "initialScrollOffset": initialScrollOffset,
    },
    children,
  );
};