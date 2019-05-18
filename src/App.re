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

[@react.component]
let make = () =>
  <Layout>
    <Nav />
    <main className=Styles.main>
      <aside className=Styles.sidebar> {React.string("Sidebar")} </aside>
      <div className=Styles.content> <Recipes /> </div>
    </main>
  </Layout>;