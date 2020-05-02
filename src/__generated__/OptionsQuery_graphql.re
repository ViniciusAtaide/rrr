/* @generated */

module Unions = {};

module Types = {
  type userByCpfCnpj = {
    name: option(string),
    cpfCnpj: string,
  };
};

open Types;

type response = {userByCpfCnpj: option(userByCpfCnpj)};
type refetchVariables = {cpfCnpj: option(string)};
let makeRefetchVariables = (~cpfCnpj=?, ()): refetchVariables => {
  cpfCnpj: cpfCnpj,
};
type variables = {cpfCnpj: string};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"userByCpfCnpj":{"n":""},"userByCpfCnpj_name":{"n":""}}} |}
  ];
  let responseConverterMap = ();
  let convertResponse = v =>
    v
    ->ReasonRelay._convertObj(
        responseConverter,
        responseConverterMap,
        Js.undefined,
      );

  let variablesConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {} |}
  ];
  let variablesConverterMap = ();
  let convertVariables = v =>
    v
    ->ReasonRelay._convertObj(
        variablesConverter,
        variablesConverterMap,
        Js.undefined,
      );
};

module Utils = {};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "cpfCnpj",
    "type": "String!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "LinkedField",
    "alias": null,
    "name": "userByCpfCnpj",
    "storageKey": null,
    "args": [
      {
        "kind": "Variable",
        "name": "cpfCnpj",
        "variableName": "cpfCnpj"
      }
    ],
    "concreteType": "User",
    "plural": false,
    "selections": [
      {
        "kind": "ScalarField",
        "alias": null,
        "name": "name",
        "args": null,
        "storageKey": null
      },
      {
        "kind": "ScalarField",
        "alias": null,
        "name": "cpfCnpj",
        "args": null,
        "storageKey": null
      }
    ]
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "OptionsQuery",
    "type": "Query",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "OptionsQuery",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "query",
    "name": "OptionsQuery",
    "id": null,
    "text": "query OptionsQuery(\n  $cpfCnpj: String!\n) {\n  userByCpfCnpj(cpfCnpj: $cpfCnpj) {\n    name\n    cpfCnpj\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
