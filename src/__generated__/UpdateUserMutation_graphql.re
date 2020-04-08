/* @generated */

module Unions = {};

module Types = {
  type userPatch = {
    _id: option(int),
    name: option(string),
    email: option(string),
    phone: option(string),
    iswhats: option(bool),
    cpfCnpj: option(string),
  };
  type updateUserByCpfCnpjInput = {
    clientMutationId: option(string),
    userPatch,
    cpfCnpj: string,
  };
  type user = {_id: int};
  type updateUserByCpfCnpj = {user: option(user)};
};

open Types;

type response = {updateUserByCpfCnpj: option(updateUserByCpfCnpj)};
type variables = {input: updateUserByCpfCnpjInput};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"updateUserByCpfCnpj":{"n":""},"updateUserByCpfCnpj_user":{"n":""}}} |}
  ];
  let wrapResponseConverterMap = ();
  let convertWrapResponse = v =>
    v
    ->ReasonRelay._convertObj(
        wrapResponseConverter,
        wrapResponseConverterMap,
        Js.null,
      );

  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"updateUserByCpfCnpj":{"n":""},"updateUserByCpfCnpj_user":{"n":""}}} |}
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
    {| {"__root":{"input":{"r":"UpdateUserByCpfCnpjInput"}},"UserPatch":{"_id":{"n":""},"name":{"n":""},"email":{"n":""},"phone":{"n":""},"iswhats":{"n":""},"cpfCnpj":{"n":""}},"UpdateUserByCpfCnpjInput":{"clientMutationId":{"n":""},"userPatch":{"r":"UserPatch"}}} |}
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

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "input",
    "type": "UpdateUserByCpfCnpjInput!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "LinkedField",
    "alias": null,
    "name": "updateUserByCpfCnpj",
    "storageKey": null,
    "args": [
      {
        "kind": "Variable",
        "name": "input",
        "variableName": "input"
      }
    ],
    "concreteType": "UpdateUserPayload",
    "plural": false,
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "user",
        "storageKey": null,
        "args": null,
        "concreteType": "User",
        "plural": false,
        "selections": [
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "_id",
            "args": null,
            "storageKey": null
          }
        ]
      }
    ]
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "UpdateUserMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "UpdateUserMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "mutation",
    "name": "UpdateUserMutation",
    "id": null,
    "text": "mutation UpdateUserMutation(\n  $input: UpdateUserByCpfCnpjInput!\n) {\n  updateUserByCpfCnpj(input: $input) {\n    user {\n      _id\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
