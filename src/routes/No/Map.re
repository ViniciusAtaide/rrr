[@bs.module "./Map/location.json"]
external mapStyle: array(Js.Json.t) = "map";

type timerId;
[@bs.val] external setTimeout: (unit => unit, int) => timerId = "setTimeout";
[@bs.val] external clearTimeout: timerId => unit = "clearTimeout";

module Query = [%relay.query
  {|
  query MapQuery {
    allPlaces {
      nodes {
        _id
        name
        longitude
        latitude
        email
        address
        phonesByPlaceId {
          nodes {
            number
            isWhats
          }
        }
      }
    }
  }
|}
];
let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~paddingHorizontal=25.->dp,
          ~flex=1.,
          (),
        ),
      "txtInput":
        style(
          ~fontFamily="Montserrat-Regular",
          ~color="#000",
          ~backgroundColor="white",
          ~fontSize=22.,
          ~padding=10.->dp,
          ~width=100.->pct,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~paddingTop=40.->dp,
          ~fontFamily="Montserrat-Regular",
          ~fontSize=22.,
          (),
        ),
      "center":
        style(
          ~justifyContent=`center,
          ~alignItems=`center,
          ~width=100.->pct,
          (),
        ),
      "mapContainer":
        style(
          ~width=100.->pct,
          ~marginVertical=10.->dp,
          ~height=60.->pct,
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  let query = Query.use(~variables=(), ());

  let (cidade, setCidade) = React.useState(_ => "");
  let mapRef = React.useRef(Js.Nullable.null);

  React.useEffect1(
    () => {
      let t =
        setTimeout(
          () => {
            mapRef
            ->React.Ref.current
            ->Js.Nullable.toOption
            ->Belt.Option.map(map =>
                map->ReactNativeMaps.MapView.fitToElements(true)
              )
            ->ignore
          },
          2000,
        );

      Some(_ => clearTimeout(t));
    },
    [|cidade|],
  );

  ReactNativeMaps.(
    ReactNative.(
      <View style={styles##bg}>
        <KeyboardAvoidingView behavior=`height style={styles##container}>
          <Text style={styles##orange}>
            {j|Encontre por estado|j}->React.string
          </Text>
          <View style={styles##mapContainer}>
            <MapView
              ref=mapRef
              provider=`google
              style=StyleSheet.absoluteFillObject
              customMapStyle=mapStyle
              region={
                "latitude": (-8.46927994062868),
                "longitude": (-54.79442719370127),
                "latitudeDelta": 52.37115432732047,
                "longitudeDelta": 41.884170323610,
              }>
              {switch (query.allPlaces) {
               | Some(places) =>
                 places.nodes
                 ->Belt.Array.keep(location =>
                     switch (location) {
                     | Some(location) =>
                       cidade === ""
                         ? true
                         : location.name
                           |> Js.String.toLowerCase
                           |> Js.String.includes(
                                cidade |> Js.String.toLowerCase,
                              )
                     | None => false
                     }
                   )
                 ->Belt.Array.map(location =>
                     switch (location) {
                     | Some(location) =>
                       <Marker
                         key={string_of_int(location._id)}
                         onPress={_ => {
                           Keyboard.dismiss();
                           navigation->Navigators.MapNavigator.Navigation.navigateWithParams(
                             "Location",
                             {location: location},
                           );
                         }}
                         title={location.name}
                         image={Image.Source.fromRequired(
                           Packager.require("./Map/map_point.png"),
                         )}
                         coordinate={
                           "latitude": location.latitude->float_of_string,
                           "longitude": location.longitude->float_of_string,
                         }
                       />
                     | None => React.null
                     }
                   )
                 ->React.array
               | None => React.null
               }}
            </MapView>
          </View>
          <TextInput
            style={Style.list([styles##txtInput])}
            onChangeText={cidade => setCidade(_ => {cidade})}
            placeholder="Ou busque por cidade"
          />
        </KeyboardAvoidingView>
      </View>
    )
  );
};