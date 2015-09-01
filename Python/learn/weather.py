# coding: utf8
import xml.etree.ElementTree as ET
import urllib

country = str(raw_input('Input county: ')).decode('utf-8')
city = str(raw_input('Input city: ')).decode('utf-8')
tree = ET.parse(urllib.urlopen('https://pogoda.yandex.ru/static/cities.xml'))

root_tree = tree.getroot()
idInputCity = 'http://export.yandex.ru/weather-ng/forecasts/'
for countries in root_tree.findall('country', tree):
    if (countries.get('name') == country):
        for cities in countries.findall('city', tree):
           if (cities.text == city):
                idInputCity += cities.get('id')

idInputCity += '.xml'

weather = ET.parse(urllib.urlopen(idInputCity))
root_weather = weather.getroot()
for fact in root_weather.findall('{http://weather.yandex.ru/forecast}fact', weather):
    for child in fact.findall('{http://weather.yandex.ru/forecast}temperature', weather):
      print 'temperature =',child.text
