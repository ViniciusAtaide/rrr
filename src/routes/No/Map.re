[@bs.module "./Map/location.json"]
external mapStyle: array(Js.Json.t) = "map";

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
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="white",
          ~paddingTop=40.->dp,
          ~fontSize=22.,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~paddingTop=40.->dp,
          ~fontFamily="Montserrat-Bold",
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

  ReactNativeMaps.(
    ReactNative.(
      <View style={styles##bg}>
        <View style={styles##container}>
          <Text style={styles##orange}>
            {j|Encontre por estado|j}->React.string
          </Text>
          <View style={styles##mapContainer}>
            <MapView
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
                 ->Belt.Array.map(location =>
                     switch (location) {
                     | Some(location) =>
                       <Marker
                         key={string_of_int(location._id)}
                         onPress={_ =>
                           navigation->Navigators.MapNavigator.Navigation.navigateWithParams(
                             "Location",
                             {location: location},
                           )
                         }
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
          <Text style={styles##txt}>
            {j|Ou busque por cidade|j}->React.string
          </Text>
        </View>
      </View>
    )
  );
};