module Styles = {
  open Css;
  let main =
    style([
      display(`grid),
      minHeight(pct(100.)),
      gridTemplateColumns([rem(25.), fr(3.)]),
      margin2(~v=rem(Theme.navHeight), ~h=`auto),
    ]);
  let sidebar = style([gridColumnStart(1)]);
  let content =
    style([marginTop(rem(2.5)), gridColumnStart(2), gridColumnEnd(2)]);
};

type page =
  | Home
  | ShoppingList;

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Home
  | ["shoppingList"] => ShoppingList
  | _ => Home
  };

type state = {route: page};
type action =
  | UpdatePage(page);

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UpdatePage(route) => {...state, route}
        },
      {route: ReasonReactRouter.useUrl() |> mapUrlToRoute},
    );
  React.useEffect0(() => {
    let watcherId =
      ReasonReact.Router.watchUrl(url =>
        dispatch(UpdatePage(url |> mapUrlToRoute))
      );
    Some(() => ReasonReact.Router.unwatchUrl(watcherId));
  });
  <Layout>
    <Nav />
    <main className=Styles.main>
      {switch (state.route) {
       | Home =>
         <>
           <aside className=Styles.sidebar> {React.string("Sidebar")} </aside>
           <div className=Styles.content> <Recipes /> </div>
         </>
       | ShoppingList => <div> {"ShoppingList" |> React.string} </div>
       }}
    </main>
  </Layout>;
};