# coding=utf-8

import requests
import json
import math
import aiohttp
import asyncio
import os
import re
import logging
from json import JSONDecodeError


class Downloader(object):

    def __init__(self):
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36',
        }
        self.session = requests.session()

    def download_file(self, url, filename):
        with self.session.get(url, headers=self.headers, stream=True) as r:
            with open(filename, 'wb') as f:
                for chunk in r.iter_content(chunk_size=1024):
                    if chunk:
                        f.write(chunk)
            print('%s finished!' % filename)


class Xmly:

    def __init__(self, download_dir=''):
        self.downloader = Downloader()
        self.album_tracks_api = 'https://www.ximalaya.com/revision/album/getTracksList?albumId={}&pageNum={}'
        self.tracks_download_api = 'http://www.ximalaya.com/tracks/{}.json'
        self.download_file = './xmly_download.txt'
        self.audio_type = 'mp4'
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36',
        }
        self.download_dir = download_dir
        self.tracks_count_per_page = 30
        self.audio_download_info = dict()
        self.__load_download_file()

    def __load_download_file(self):
        if os.path.isfile(self.download_file):
            with open(self.download_file, 'r', encoding='utf-8') as f:
                for line in f.read().splitlines():
                    k, v = line.split(',')
                    self.audio_download_info.update({k: v})

    def __save_download_file(self):
        with open(self.download_file, 'w', encoding='utf-8') as f:
            for k in self.audio_download_info.keys():
                v = self.audio_download_info.get(k)
                format_str = '{},{}\n'.format(k, v)
                f.write(format_str)

    def fetch(self, urls):
        if isinstance(urls, str):
            return requests.get(urls, headers=self.headers).text
        elif isinstance(urls, list):
            return [requests.get(url, headers=self.headers).text for url in urls]

    def get_tracks_pages(self, id):
        '''
            获取专辑音频列表总页数
        '''
        html = self.fetch(self.album_tracks_api.format(id, str(1)))
        json_text = json.loads(html)
        total_count = json_text['data']['trackTotalCount']
        pages = math.ceil(int(total_count) / self.tracks_count_per_page)
        return pages

    def get_all_track_info(self, id):
        '''
            获取所有音频的信息
        '''
        pages = self.get_tracks_pages(id)
        tracks_urls = [self.album_tracks_api.format(str(id), str(page)) for page in range(1, pages + 1)]
        json_text = self.fetch(tracks_urls)

        tracks_info = dict()
        for item in json_text:
            titles = re.findall('"title":"(.*?)",', item)
            tracks_id = re.findall('"trackId":(\d+),', item)
            tracks_info.update(dict(zip(titles, tracks_id)))

        return tracks_info

    def get_all_audio_download_url(self, id):
        '''
            获取所有音频的下载链接
        '''
        tracks_info = self.get_all_track_info(id)
        tracks_urls = [self.tracks_download_api.format(track_id) for track_id in list(tracks_info.values())]
        json_text = self.fetch(tracks_urls)

        audio_download_urls = list()
        for item in json_text:
            audio_download_urls.append(json.loads(item)['play_path'])
        self.audio_download_info.update(dict(zip(list(tracks_info.keys()), audio_download_urls)))
        self.__save_download_file()

    def download(self, id):
        if self.audio_download_info:
            for item in self.audio_download_info.items():
                url = item[1]
                filename = os.path.join(self.download_dir, '.'.join([item[0], self.audio_type]))
                self.downloader.download_file(url=url, filename=filename)
        else:
            self.get_all_audio_download_url(id)
            self.download(id)


if __name__ == '__main__':
    xmly = Xmly()
    xmly.download('9283606')
    print(xmly.audio_download_info)
