open Jest;
open Expect;
open ReactTestingLibrary;

describe("<Nav />", () => {
  test("renders", () => {
    let result = render(<Nav />);
    result |> container |> expect |> toMatchSnapshot;
  });

  test("should contain a header with 'Recipe Book'", () => {
    let result = render(<Nav />);
    result
    |> getByText(~matcher=`Str("Recipe Book"))
    |> expect
    |> ExpectJs.toBeTruthy;
  });
});