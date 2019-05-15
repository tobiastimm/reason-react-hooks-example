module Styles = {
  open Css;
  let main =
    style([
      maxWidth(rem(55.)),
      paddingLeft(rem(1.6)),
      paddingRight(rem(1.6)),
      margin2(~v=rem(Theme.navHeight), ~h=`auto),
    ]);
};

[@react.component]
let make = () =>
  <Layout>
    <Nav />
    <div className=Styles.main> {React.string("HELLO")} </div>
  </Layout>;