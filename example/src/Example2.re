type state = {scrollToIndex: int};

type action =
  | UpdateScrollToIndex(int);

let reducer = (action, _state) =>
  switch (action) {
  | UpdateScrollToIndex(value) => ReasonReact.Update({scrollToIndex: value})
  };

let component = ReasonReact.reducerComponent("Example2");

let make = _children => {
  ...component,
  initialState: () => {scrollToIndex: (-1)},
  reducer,
  render: self => {
    let list = [|
      "George",
      "Lisa",
      "Ahmed",
      "Rhys",
      "Rachel",
      "Fatima",
      "Alberto",
      "Sarah",
      "Seamus",
      "Buddy",
      "Renae",
      "Kevin",
      "Marylin",
      "Edith",
      "Keith",
      "Ismo",
      "Guadalupe",
      "Zelma",
      "Ellis",
      "Johnson",
      "Dorin",
      "John",
      "Jasper",
      "Jasmine",
      "Scott",
      "Samir",
      "Lauren",
      "Elizabeth",
      "Zorro",
      "Ishmael",
      "Moises",
    |];
    let noRowsRenderer = () => <div> (ReasonReact.string("No rows")) </div>;
    let rowRenderer = (rowRenderParams: List.rowRenderParams) => {
      let row = list[rowRenderParams |. List.index];
      <div key=(rowRenderParams |. List.key)>
        (ReasonReact.string(row))
      </div>;
    };
    <div>
      <List
        strRef="List"
        height=300
        overscanRowCount=10
        rowCount=(Array.length(list))
        rowHeight=50
        noRowsRenderer
        rowRenderer
        scrollToIndex=0
        width=300
      />
    </div>;
  },
};
