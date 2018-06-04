[@bs.module "react-virtualized"]
external list : ReasonReact.reactClass = "List";

[@bs.deriving abstract]
type rowRenderParams = {
  index: int,
  key: string,
  isScrolling: bool,
  isVisible: bool,
  /* parent */
  /* style */
};

let make = (~autoHeight=false,
            ~className="",
            ~isScrolling=false,
            ~onScroll=()=>(),
            ~height: int,
            ~noRowsRenderer=()=>(),
            ~overscanRowCount: int,
            ~rowCount: int,
            ~rowHeight: int,
            ~rowRenderer: rowRenderParams => ReasonReact.reactElement,
            ~scrollToIndex: int,
            ~scrollTop,
            ~width: int,
            children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=list,
    ~props={
      "autoHeight": autoHeight,
      "className": className,
      "height": height,
      "isScrolling": isScrolling,
      "noRowsRendered": noRowsRenderer,
      "onScroll": onScroll,
      "overscanRowCount": overscanRowCount,
      "width": width,
      "rowCount": rowCount,
      "rowHeight": rowHeight,
      "rowRenderer": rowRenderer,
      "scrollToIndex": scrollToIndex,
      "scrollTop": scrollTop
    },
    children
  );
};
