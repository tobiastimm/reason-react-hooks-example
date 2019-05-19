module Edit = {
  type props = {
    .
    "size": int,
    "color": string,
  };

  [@bs.module "react-feather"] external make: props => React.element = "Edit";

  let makeProps = (~size=24, ~color="#333", ()): props => {
    "size": size,
    "color": color,
  };
};