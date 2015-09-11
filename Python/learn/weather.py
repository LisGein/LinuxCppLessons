#!/usr/bin/env python3
#  coding: utf8
import xml.etree.ElementTree as ET
import urllib.request
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('country', type=str, help='country help')
parser.add_argument('city', type=str, help='city help')
args = parser.parse_args()

tree = ET.parse(urllib.request.urlopen('https://pogoda.yandex.ru/static/cities.xml'))

root_tree = tree.getroot()
idInputCity = 'http://export.yandex.ru/weather-ng/forecasts/'
for countries in root_tree.findall('country'):
    if (countries.get('name') == args.country):
        for cities in countries.findall('city'):
           if (cities.text == args.city):
                idInputCity += cities.get('id')

idInputCity += '.xml'

weather = ET.parse(urllib.request.urlopen(idInputCity))
root_weather = weather.getroot()
for fact in root_weather.findall('{http://weather.yandex.ru/forecast}fact'):
    for child in fact.findall('{http://weather.yandex.ru/forecast}temperature'):
      print('temperature ='+child.text)
