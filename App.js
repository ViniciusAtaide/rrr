/**
 * Do not modify this file - it is a proxy to your `App.re` file
 * located in the `src/` folder.
 */
import 'react-native-gesture-handler';

import React, {useEffect} from 'react';
import {StyleSheet, Platform, StatusBar} from 'react-native';
import {app as ReasonApp} from './src/App.bs.js';
import {NavigationContainer} from '@react-navigation/native';
import SplashScreen from 'react-native-splash-screen';

export default function App() {
  useEffect(() => {
    SplashScreen.hide();
  }, []);
  return (
    <NavigationContainer>
      {Platform.OS === 'ios' && <StatusBar barStyle="dark-content" />}
      <ReasonApp class={styles.container} />
    </NavigationContainer>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
