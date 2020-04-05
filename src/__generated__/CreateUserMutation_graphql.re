/* @generated */

module Unions = {};

module Types = {
  type userInput = {
    _id: option(int),
    name: string,
    email: string,
    cpfCnpj: string,
  };
  type createUserInput = {
    clientMutationId: option(string),
    user: userInput,
  };
  type node = {
    name: string,
    _id: int,
    email: string,
    nodeId: string,
  };
  type userEdge = {node: option(node)};
  type createUser = {userEdge: option(userEdge)};
};

open Types;

type response = {createUser: option(createUser)};
type variables = {input: createUserInput};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"createUser":{"n":""},"createUser_userEdge":{"n":""},"createUser_userEdge_node":{"n":""}}} |}
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
    {| {"__root":{"createUser":{"n":""},"createUser_userEdge":{"n":""},"createUser_userEdge_node":{"n":""}}} |}
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
    {| {"__root":{"input":{"r":"CreateUserInput"}},"UserInput":{"_id":{"n":""}},"CreateUserInput":{"clientMutationId":{"n":""},"user":{"r":"UserInput"}}} |}
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
    "type": "CreateUserInput!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "LinkedField",
    "alias": null,
    "name": "createUser",
    "storageKey": null,
    "args": [
      {
        "kind": "Variable",
        "name": "input",
        "variableName": "input"
      }
    ],
    "concreteType": "CreateUserPayload",
    "plural": false,
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "userEdge",
        "storageKey": null,
        "args": null,
        "concreteType": "UsersEdge",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "node",
            "storageKey": null,
            "args": null,
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
                "name": "_id",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "email",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "nodeId",
                "args": null,
                "storageKey": null
              }
            ]
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
    "name": "CreateUserMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "CreateUserMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "mutation",
    "name": "CreateUserMutation",
    "id": null,
    "text": "mutation CreateUserMutation(\n  $input: CreateUserInput!\n) {\n  createUser(input: $input) {\n    userEdge {\n      node {\n        name\n        _id\n        email\n        nodeId\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
