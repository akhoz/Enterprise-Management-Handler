import scrapy
import json


class IGSpider(scrapy.Spider):
    name = "IG"
    start_urls = ["https://www.instant-gaming.com/en/games/steam/"]
    game_list = []

    def parse(self, response):
        game_items = response.xpath('//div[@class="search listing-items"]//div[@class="item force-badge"]')

        for game_info in game_items:
            name = game_info.xpath('.//span[@class="title"]/text()').get()
            price = game_info.xpath('.//div[@class="price"]/text()').get()
            discount = game_info.xpath('.//div[@class="discount"]/text()').get()

            if name and price and discount:
                game = {
                    'name': name,
                    'price': price,
                    'discount': discount
                }
                self.game_list.append(game)
        with open('game_list.json', 'w') as f:
            # indent = 4
            json.dump(self.game_list, f, indent=4)



