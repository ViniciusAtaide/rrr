[@bs.module "./Location/location.json"]
external mapStyle: array(Js.Json.t) = "map";

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~paddingHorizontal=25.->dp,
          ~paddingVertical=60.->dp,
          ~flex=1.,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-Regular",
          ~color="white",
          ~paddingTop=40.->dp,
          ~fontSize=18.,
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
          ~justifyContent=`spaceAround,
          ~alignItems=`center,
          ~width=100.->pct,
          (),
        ),
      "mapContainer": style(~width=100.->pct, ~height=70.->pct, ()),
    })
  );

[@react.component]
let make = (~navigation as _, ~route as _) => {
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
              <Marker
                title="João Pessoa | PB"
                description="João Pessoa - Unidade Bancários"
                image={Image.Source.fromRequired(
                  Packager.require("./Location/map_point.png"),
                )}
                coordinate={
                  "latitude": (-8.46927994062868),
                  "longitude": (-54.79442719370127),
                }
              />
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