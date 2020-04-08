module Async = {
  include Promise;
  let let_ = Promise.flatMap;

  module Wrap = {
    let let_ = Promise.map;
  };
};

module Email = {
  type t = string;

  let emailRegexp = [%re "/[^@]+@[^\\.]+\\..+/"];

  let validate = email => email |> Js.String.match(emailRegexp);
};